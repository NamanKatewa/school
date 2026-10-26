"""
Task 2: Unsupervised ML for Anomaly Detection
Author: Naman Katewa | Roll No: 2401830002 | Course: B.Sc.(H) Cybersecurity
"""

import time
import json
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.cluster import KMeans, DBSCAN
from sklearn.ensemble import IsolationForest
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from sklearn.neighbors import NearestNeighbors
from sklearn.metrics import (
    silhouette_score,
    adjusted_rand_score,
    normalized_mutual_info_score,
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    roc_auc_score,
    confusion_matrix
)

def main():
    print("=" * 70)
    print("TASK 2: UNSUPERVISED ML FOR ANOMALY DETECTION")
    print("Student: Naman Katewa | Roll No: 2401830002 | Course: B.Sc.(H) Cybersecurity")
    print("=" * 70)

    # 1. Column Names
    col_names = [
        "duration", "protocol_type", "service", "flag", "src_bytes", "dst_bytes",
        "land", "wrong_fragment", "urgent", "hot", "num_failed_logins", "logged_in",
        "num_compromised", "root_shell", "su_attempted", "num_root", "num_file_creations",
        "num_shells", "num_access_files", "num_outbound_cmds", "is_host_login",
        "is_guest_login", "count", "srv_count", "serror_rate", "srv_serror_rate",
        "rerror_rate", "srv_rerror_rate", "same_srv_rate", "diff_srv_rate",
        "srv_diff_host_rate", "dst_host_count", "dst_host_srv_count",
        "dst_host_same_srv_rate", "dst_host_diff_srv_rate", "dst_host_same_src_port_rate",
        "dst_host_srv_diff_host_rate", "dst_host_serror_rate", "dst_host_srv_serror_rate",
        "dst_host_rerror_rate", "dst_host_srv_rerror_rate", "attack_type", "difficulty_level"
    ]

    print("\n[+] Loading NSL-KDD dataset...")
    df = pd.read_csv("data/nsl_kdd.csv", names=col_names, header=None)
    df['is_intrusion'] = (df['attack_type'] != 'normal').astype(int)

    # 2. Stratified Sampling for tractable density clustering & t-SNE
    from sklearn.model_selection import train_test_split
    sample_size = 6000
    _, df_sample = train_test_split(df, test_size=sample_size, stratify=df['is_intrusion'], random_state=42)
    df_sample = df_sample.reset_index(drop=True)
    print(f"    Subsampled {len(df_sample)} records (Preserving Normal: {sum(df_sample['is_intrusion']==0)}, Attack: {sum(df_sample['is_intrusion']==1)})")

    # 3. Preprocessing (Strictly Unsupervised: Labels excluded from feature matrix)
    features_df = df_sample.drop(columns=['attack_type', 'difficulty_level', 'is_intrusion'])
    cat_cols = ['protocol_type', 'service', 'flag']
    encoded_df = features_df.copy()
    for col in cat_cols:
        le = LabelEncoder()
        encoded_df[col] = le.fit_transform(encoded_df[col])

    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(encoded_df.values)
    y_true = df_sample['is_intrusion'].values

    # 4. K-Means Clustering: Elbow Method & Silhouette Scores
    print("\n" + "=" * 50)
    print("APPLYING K-MEANS CLUSTERING & ELBOW METHOD")
    print("=" * 50)
    k_range = list(range(2, 9))
    inertias = []
    silhouette_scores_k = []

    for k in k_range:
        km = KMeans(n_clusters=k, random_state=42, n_init=10)
        km.fit(X_scaled)
        inertias.append(km.inertia_)
        sil = silhouette_score(X_scaled, km.labels_, sample_size=2000, random_state=42)
        silhouette_scores_k.append(sil)
        print(f"  k = {k}: Inertia = {km.inertia_:10.2f} | Silhouette Score = {sil:.4f}")

    # Optimal k selection: k=2 for binary normal vs attack partition
    optimal_k = 2
    km_optimal = KMeans(n_clusters=optimal_k, random_state=42, n_init=10)
    km_labels = km_optimal.fit_predict(X_scaled)

    # Map cluster to anomaly: cluster with higher ground truth anomaly concentration
    cluster_0_anomalies = np.mean(y_true[km_labels == 0])
    cluster_1_anomalies = np.mean(y_true[km_labels == 1])
    km_anomaly_pred = km_labels if cluster_1_anomalies > cluster_0_anomalies else (1 - km_labels)

    km_acc = accuracy_score(y_true, km_anomaly_pred)
    km_f1 = f1_score(y_true, km_anomaly_pred)
    km_ari = adjusted_rand_score(y_true, km_labels)
    km_nmi = normalized_mutual_info_score(y_true, km_labels)
    print(f"\n  [Optimal k = {optimal_k} Evaluation]")
    print(f"  Accuracy (Aligned): {km_acc*100:.2f}% | F1: {km_f1*100:.2f}% | ARI: {km_ari:.4f} | NMI: {km_nmi:.4f}")

    # Generate Figure: Elbow & Silhouette Plot
    fig, ax1 = plt.subplots(figsize=(8, 5))
    color = '#1f77b4'
    ax1.set_xlabel('Number of Clusters (k)', fontsize=11, fontweight='bold')
    ax1.set_ylabel('Inertia (Within-Cluster Sum of Squares)', color=color, fontsize=11, fontweight='bold')
    line1 = ax1.plot(k_range, inertias, 'o-', color=color, linewidth=2.5, markersize=8, label='Inertia (Elbow)')
    ax1.tick_params(axis='y', labelcolor=color)
    ax1.grid(True, linestyle=':', alpha=0.5)

    ax2 = ax1.twinx()
    color = '#d95f02'
    ax2.set_ylabel('Silhouette Score', color=color, fontsize=11, fontweight='bold')
    line2 = ax2.plot(k_range, silhouette_scores_k, 's--', color=color, linewidth=2.2, markersize=7, label='Silhouette Score')
    ax2.tick_params(axis='y', labelcolor=color)

    # Annotate optimal k elbow
    ax1.annotate('Optimal Elbow (k=2)', xy=(2, inertias[0]), xytext=(3, inertias[0] * 0.95),
                 arrowprops=dict(facecolor='black', shrink=0.08, width=1.5, headwidth=7),
                 fontweight='bold', fontsize=10)

    lines = line1 + line2
    labels = [l.get_label() for l in lines]
    ax1.legend(lines, labels, loc='upper right', frameon=True)
    plt.title('K-Means Parameter Optimization: Elbow Method & Silhouette Curve', fontsize=12, fontweight='bold')
    plt.tight_layout()
    plt.savefig('figures/task2/kmeans_elbow_silhouette.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task2/kmeans_elbow_silhouette.png")

    # 5. DBSCAN Clustering: Parameter Selection & Evaluation
    print("\n" + "=" * 50)
    print("APPLYING DBSCAN & PARAMETER JUSTIFICATION")
    print("=" * 50)
    # Justification: min_samples = 2 * n_features = 2 * 41 = 82 (Ester et al. heuristic)
    min_samples = 2 * X_scaled.shape[1]
    k_nn = min_samples - 1

    print(f"  Calculating {k_nn}-NN distances for {X_scaled.shape[0]} points to identify optimal eps...")
    nbrs = NearestNeighbors(n_neighbors=k_nn).fit(X_scaled)
    distances, _ = nbrs.kneighbors(X_scaled)
    sorted_k_dist = np.sort(distances[:, -1])

    # Finding elbow/knee in k-distance graph:
    # 90th - 95th percentile represents transition from dense core to sparse noise
    optimal_eps = float(np.percentile(sorted_k_dist, 93))
    optimal_eps = round(optimal_eps, 2)
    print(f"  Theoretical min_samples: {min_samples} (2 * {X_scaled.shape[1]} features)")
    print(f"  Empirical knee eps identified: {optimal_eps}")

    # Plot Figure: k-distance graph
    plt.figure(figsize=(8, 5))
    plt.plot(sorted_k_dist, color='#2b5c8f', linewidth=2)
    plt.axhline(y=optimal_eps, color='#e41a1c', linestyle='--', linewidth=2, label=f'Chosen eps = {optimal_eps}')
    plt.xlabel('Points sorted by distance', fontsize=11, fontweight='bold')
    plt.ylabel(f'{k_nn}-NN Distance', fontsize=11, fontweight='bold')
    plt.title(f'DBSCAN Parameter Selection: k-Distance Graph (k={k_nn})', fontsize=12, fontweight='bold')
    plt.legend(loc='upper left', frameon=True, fontsize=10)
    plt.grid(True, linestyle=':', alpha=0.5)
    plt.tight_layout()
    plt.savefig('figures/task2/dbscan_kdistance_graph.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task2/dbscan_kdistance_graph.png")

    # Fit DBSCAN
    db = DBSCAN(eps=optimal_eps, min_samples=min_samples)
    db_labels = db.fit_predict(X_scaled)
    n_clusters_db = len(set(db_labels)) - (1 if -1 in db_labels else 0)
    n_noise_db = np.sum(db_labels == -1)
    noise_ratio = n_noise_db / len(db_labels)
    print(f"  DBSCAN Clusters Found: {n_clusters_db}")
    print(f"  Noise Points Detected (-1 as Anomaly): {n_noise_db} ({noise_ratio*100:.2f}%)")

    # DBSCAN Anomaly evaluation: Noise (-1) treated as anomaly (1), non-noise as normal (0)
    db_anomaly_pred = (db_labels == -1).astype(int)
    db_acc = accuracy_score(y_true, db_anomaly_pred)
    db_prec = precision_score(y_true, db_anomaly_pred, zero_division=0)
    db_rec = recall_score(y_true, db_anomaly_pred, zero_division=0)
    db_f1 = f1_score(y_true, db_anomaly_pred, zero_division=0)
    print(f"  DBSCAN Anomaly Detection -> Acc: {db_acc*100:.2f}% | Prec: {db_prec*100:.2f}% | Rec: {db_rec*100:.2f}% | F1: {db_f1*100:.2f}%")

    # 6. Isolation Forest for Outlier Detection
    print("\n" + "=" * 50)
    print("APPLYING ISOLATION FOREST")
    print("=" * 50)
    contamination_rate = np.mean(y_true)
    print(f"  Contamination rate set to empirical intrusion ratio: {contamination_rate:.4f}")
    iso_forest = IsolationForest(n_estimators=100, contamination=contamination_rate, random_state=42, n_jobs=-1)
    iso_preds = iso_forest.fit_predict(X_scaled)
    # IsolationForest returns -1 for outliers and 1 for inliers
    iso_anomaly_pred = (iso_preds == -1).astype(int)
    iso_scores = -iso_forest.decision_function(X_scaled)

    iso_acc = accuracy_score(y_true, iso_anomaly_pred)
    iso_prec = precision_score(y_true, iso_anomaly_pred)
    iso_rec = recall_score(y_true, iso_anomaly_pred)
    iso_f1 = f1_score(y_true, iso_anomaly_pred)
    iso_auc = roc_auc_score(y_true, iso_scores)
    print(f"  Isolation Forest -> Acc: {iso_acc*100:.2f}% | Prec: {iso_prec*100:.2f}% | Rec: {iso_rec*100:.2f}% | F1: {iso_f1*100:.2f}% | AUC: {iso_auc:.4f}")

    # 7. Dimensionality Reduction & Visualizations (PCA & t-SNE)
    print("\n" + "=" * 50)
    print("DIMENSIONALITY REDUCTION (PCA & t-SNE)")
    print("=" * 50)
    print("  Computing PCA (2 Components)...")
    pca = PCA(n_components=2, random_state=42)
    X_pca = pca.fit_transform(X_scaled)
    var_exp = pca.explained_variance_ratio_
    print(f"  PCA Explained Variance: PC1={var_exp[0]*100:.2f}%, PC2={var_exp[1]*100:.2f}% (Total={sum(var_exp)*100:.2f}%)")

    print("  Computing t-SNE (2 Components, Perplexity=35)...")
    t0 = time.time()
    tsne = TSNE(n_components=2, perplexity=35, random_state=42, max_iter=1000)
    X_tsne = tsne.fit_transform(X_scaled)
    print(f"  t-SNE computation completed in {time.time()-t0:.2f} s")

    # Generate Figure: 8-Panel Visualizations (4 PCA + 4 t-SNE)
    fig, axes = plt.subplots(2, 4, figsize=(20, 10))

    # Row 1: PCA
    axes[0, 0].scatter(X_pca[y_true==0, 0], X_pca[y_true==0, 1], c='#2b5c8f', label='Normal', s=10, alpha=0.5)
    axes[0, 0].scatter(X_pca[y_true==1, 0], X_pca[y_true==1, 1], c='#e41a1c', label='Intrusion', s=10, alpha=0.5)
    axes[0, 0].set_title('PCA: Ground Truth', fontweight='bold', fontsize=11)
    axes[0, 0].set_ylabel('Principal Component 2', fontweight='bold')
    axes[0, 0].legend(loc='upper right')

    axes[0, 1].scatter(X_pca[km_anomaly_pred==0, 0], X_pca[km_anomaly_pred==0, 1], c='#2b5c8f', label='Cluster 0', s=10, alpha=0.5)
    axes[0, 1].scatter(X_pca[km_anomaly_pred==1, 0], X_pca[km_anomaly_pred==1, 1], c='#e41a1c', label='Cluster 1 (Anom)', s=10, alpha=0.5)
    axes[0, 1].set_title(f'PCA: K-Means (k=2)\nAcc: {km_acc*100:.1f}%', fontweight='bold', fontsize=11)
    axes[0, 1].legend(loc='upper right')

    axes[0, 2].scatter(X_pca[db_labels!=-1, 0], X_pca[db_labels!=-1, 1], c='#2b5c8f', label='Core Clusters', s=10, alpha=0.5)
    axes[0, 2].scatter(X_pca[db_labels==-1, 0], X_pca[db_labels==-1, 1], c='#ff7f00', label='DBSCAN Noise (-1)', s=12, alpha=0.7)
    axes[0, 2].set_title(f'PCA: DBSCAN\nNoise Ratio: {noise_ratio*100:.1f}%', fontweight='bold', fontsize=11)
    axes[0, 2].legend(loc='upper right')

    axes[0, 3].scatter(X_pca[iso_anomaly_pred==0, 0], X_pca[iso_anomaly_pred==0, 1], c='#2b5c8f', label='Inliers', s=10, alpha=0.5)
    axes[0, 3].scatter(X_pca[iso_anomaly_pred==1, 0], X_pca[iso_anomaly_pred==1, 1], c='#984ea3', label='Outliers (IsoForest)', s=10, alpha=0.5)
    axes[0, 3].set_title(f'PCA: Isolation Forest\nF1: {iso_f1*100:.1f}%', fontweight='bold', fontsize=11)
    axes[0, 3].legend(loc='upper right')

    # Row 2: t-SNE
    axes[1, 0].scatter(X_tsne[y_true==0, 0], X_tsne[y_true==0, 1], c='#2b5c8f', label='Normal', s=10, alpha=0.5)
    axes[1, 0].scatter(X_tsne[y_true==1, 0], X_tsne[y_true==1, 1], c='#e41a1c', label='Intrusion', s=10, alpha=0.5)
    axes[1, 0].set_title('t-SNE: Ground Truth', fontweight='bold', fontsize=11)
    axes[1, 0].set_ylabel('t-SNE Dimension 2', fontweight='bold')
    axes[1, 0].set_xlabel('t-SNE Dimension 1', fontweight='bold')
    axes[1, 0].legend(loc='upper right')

    axes[1, 1].scatter(X_tsne[km_anomaly_pred==0, 0], X_tsne[km_anomaly_pred==0, 1], c='#2b5c8f', label='Cluster 0', s=10, alpha=0.5)
    axes[1, 1].scatter(X_tsne[km_anomaly_pred==1, 0], X_tsne[km_anomaly_pred==1, 1], c='#e41a1c', label='Cluster 1 (Anom)', s=10, alpha=0.5)
    axes[1, 1].set_title(f't-SNE: K-Means (k=2)', fontweight='bold', fontsize=11)
    axes[1, 1].set_xlabel('t-SNE Dimension 1', fontweight='bold')
    axes[1, 1].legend(loc='upper right')

    axes[1, 2].scatter(X_tsne[db_labels!=-1, 0], X_tsne[db_labels!=-1, 1], c='#2b5c8f', label='Core Clusters', s=10, alpha=0.5)
    axes[1, 2].scatter(X_tsne[db_labels==-1, 0], X_tsne[db_labels==-1, 1], c='#ff7f00', label='DBSCAN Noise (-1)', s=12, alpha=0.7)
    axes[1, 2].set_title(f't-SNE: DBSCAN', fontweight='bold', fontsize=11)
    axes[1, 2].set_xlabel('t-SNE Dimension 1', fontweight='bold')
    axes[1, 2].legend(loc='upper right')

    axes[1, 3].scatter(X_tsne[iso_anomaly_pred==0, 0], X_tsne[iso_anomaly_pred==0, 1], c='#2b5c8f', label='Inliers', s=10, alpha=0.5)
    axes[1, 3].scatter(X_tsne[iso_anomaly_pred==1, 0], X_tsne[iso_anomaly_pred==1, 1], c='#984ea3', label='Outliers (IsoForest)', s=10, alpha=0.5)
    axes[1, 3].set_title(f't-SNE: Isolation Forest', fontweight='bold', fontsize=11)
    axes[1, 3].set_xlabel('t-SNE Dimension 1', fontweight='bold')
    axes[1, 3].legend(loc='upper right')

    for ax in axes.flat:
        ax.grid(True, linestyle=':', alpha=0.4)

    plt.suptitle('Unsupervised Anomaly Detection: PCA vs t-SNE Cluster Projections', fontsize=14, fontweight='bold', y=0.99)
    plt.tight_layout()
    plt.savefig('figures/task2/pca_tsne_cluster_visualizations.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task2/pca_tsne_cluster_visualizations.png")

    # Figure: Comparative Metrics Bar Chart
    methods = ['K-Means (k=2)', 'DBSCAN (Noise as Anomaly)', 'Isolation Forest']
    accs = [km_acc * 100, db_acc * 100, iso_acc * 100]
    precs = [precision_score(y_true, km_anomaly_pred) * 100, db_prec * 100, iso_prec * 100]
    recs = [recall_score(y_true, km_anomaly_pred) * 100, db_rec * 100, iso_rec * 100]
    f1s = [km_f1 * 100, db_f1 * 100, iso_f1 * 100]

    plt.figure(figsize=(10, 5))
    x = np.arange(len(methods))
    width = 0.2
    plt.bar(x - 1.5*width, accs, width, label='Accuracy', color='#2b5c8f')
    plt.bar(x - 0.5*width, precs, width, label='Precision', color='#377eb8')
    plt.bar(x + 0.5*width, recs, width, label='Recall', color='#4daf4a')
    plt.bar(x + 1.5*width, f1s, width, label='F1-Score', color='#e41a1c')

    plt.xlabel('Unsupervised ML Technique', fontsize=11, fontweight='bold')
    plt.ylabel('Score (%)', fontsize=11, fontweight='bold')
    plt.title('Unsupervised Anomaly Detection Efficacy Against Ground Truth', fontsize=12, fontweight='bold')
    plt.xticks(x, methods, fontsize=10, fontweight='bold')
    plt.ylim([0, 105])
    plt.legend(loc='upper right', frameon=True)
    plt.grid(axis='y', linestyle=':', alpha=0.5)
    plt.tight_layout()
    plt.savefig('figures/task2/unsupervised_metrics_comparison.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task2/unsupervised_metrics_comparison.png")

    # Save summary data
    task2_results = {
        "sample_size": sample_size,
        "features_count": X_scaled.shape[1],
        "kmeans": {
            "k_range": k_range,
            "inertias": inertias,
            "silhouette_scores": silhouette_scores_k,
            "optimal_k": optimal_k,
            "accuracy": km_acc,
            "f1_score": km_f1,
            "ari": km_ari,
            "nmi": km_nmi
        },
        "dbscan": {
            "min_samples": int(min_samples),
            "optimal_eps": float(optimal_eps),
            "clusters_found": int(n_clusters_db),
            "noise_points": int(n_noise_db),
            "noise_ratio": float(noise_ratio),
            "accuracy": db_acc,
            "precision": db_prec,
            "recall": db_rec,
            "f1_score": db_f1
        },
        "isolation_forest": {
            "contamination": float(contamination_rate),
            "accuracy": iso_acc,
            "precision": iso_prec,
            "recall": iso_rec,
            "f1_score": iso_f1,
            "roc_auc": iso_auc
        },
        "pca": {
            "explained_variance_ratio": var_exp.tolist(),
            "total_variance": float(sum(var_exp))
        }
    }
    with open("output/task2_results.json", "w") as f:
        json.dump(task2_results, f, indent=4)
    print("[+] Saved output/task2_results.json")
    print("\n[V] TASK 2 COMPLETED SUCCESSFULLY.")

if __name__ == '__main__':
    main()
