"""
Task 1: Supervised ML Classifiers for Network Intrusion Detection
Author: Naman Katewa | Roll No: 2401830002 | Course: B.Sc.(H) Cybersecurity
"""

import time
import json
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    roc_auc_score,
    roc_curve,
    confusion_matrix,
    classification_report
)

def main():
    print("=" * 70)
    print("TASK 1: SUPERVISED ML CLASSIFIERS FOR NETWORK INTRUSION DETECTION")
    print("Student: Naman Katewa | Roll No: 2401830002 | Course: B.Sc.(H) Cybersecurity")
    print("=" * 70)

    # 1. Column Names Definition based on NSL-KDD specification
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

    # 2. Load Dataset
    print("\n[+] Loading NSL-KDD dataset from data/nsl_kdd.csv...")
    df = pd.read_csv("data/nsl_kdd.csv", names=col_names, header=None)
    print(f"    Dataset loaded: {df.shape[0]} rows, {df.shape[1]} columns")

    # 3. Attack Taxonomy Mapping (4 major families)
    dos_attacks = ['apache2', 'back', 'land', 'mailbomb', 'neptune', 'pod', 'processtable', 'smurf', 'teardrop', 'udpstorm']
    probe_attacks = ['ipsweep', 'mscan', 'nmap', 'portsweep', 'saint', 'satan']
    r2l_attacks = ['ftp_write', 'guess_passwd', 'httptunnel', 'imap', 'multihop', 'named', 'phf', 'sendmail',
                   'snmpgetattack', 'snmpguess', 'spy', 'warezclient', 'warezmaster', 'worm', 'xlock', 'xsnoop']
    u2r_attacks = ['buffer_overflow', 'loadmodule', 'perl', 'ps', 'rootkit', 'sqlattack', 'xterm']

    def map_attack(label):
        lbl = str(label).strip().lower()
        if lbl == 'normal':
            return 'Normal'
        elif lbl in dos_attacks:
            return 'DoS'
        elif lbl in probe_attacks:
            return 'Probe'
        elif lbl in r2l_attacks:
            return 'R2L'
        elif lbl in u2r_attacks:
            return 'U2R'
        else:
            return 'Other_Attack'

    df['attack_class'] = df['attack_type'].apply(map_attack)
    df['is_intrusion'] = (df['attack_class'] != 'Normal').astype(int)

    # 4. Dataset Exploration
    print("\n" + "=" * 50)
    print("DATASET EXPLORATION & CLASS DISTRIBUTION")
    print("=" * 50)
    print(f"Total Records: {len(df)}")
    print(f"Missing Values: {df.isnull().sum().sum()}")
    print("\nBinary Class Distribution:")
    binary_counts = df['is_intrusion'].value_counts()
    print(f"  Normal (0): {binary_counts.get(0, 0)} ({binary_counts.get(0, 0)/len(df)*100:.2f}%)")
    print(f"  Attack (1): {binary_counts.get(1, 0)} ({binary_counts.get(1, 0)/len(df)*100:.2f}%)")

    print("\n5-Class Taxonomy Distribution:")
    cat_counts = df['attack_class'].value_counts()
    for cat, cnt in cat_counts.items():
        print(f"  {cat:10s}: {cnt:6d} ({cnt/len(df)*100:6.2f}%)")

    # Generate Figure 1: Class Distribution
    fig, axes = plt.subplots(1, 2, figsize=(13, 5))
    palette_binary = ['#2b5c8f', '#d95f02']
    sns.countplot(x='is_intrusion', data=df, ax=axes[0], palette=palette_binary, hue='is_intrusion', legend=False)
    axes[0].set_title('Binary Distribution: Normal (0) vs Attack (1)', fontsize=12, fontweight='bold')
    axes[0].set_xticklabels(['Normal (0)', 'Intrusion (1)'])
    axes[0].set_ylabel('Record Count')
    for p in axes[0].patches:
        axes[0].annotate(f"{int(p.get_height())}\n({p.get_height()/len(df)*100:.1f}%)",
                         (p.get_x() + p.get_width() / 2., p.get_height() / 2.),
                         ha='center', va='center', color='white', fontweight='bold', fontsize=11)

    order_cat = ['Normal', 'DoS', 'Probe', 'R2L', 'U2R']
    present_order = [c for c in order_cat if c in df['attack_class'].unique()]
    palette_multi = ['#2b5c8f', '#e41a1c', '#377eb8', '#4daf4a', '#984ea3']
    sns.countplot(x='attack_class', data=df, order=present_order, ax=axes[1], palette=palette_multi[:len(present_order)], hue='attack_class', legend=False)
    axes[1].set_title('Multi-Class Attack Taxonomy Distribution', fontsize=12, fontweight='bold')
    axes[1].set_ylabel('Record Count')
    axes[1].set_xlabel('Traffic Category')
    for p in axes[1].patches:
        h = p.get_height()
        if h > 0:
            axes[1].annotate(f"{int(h)}", (p.get_x() + p.get_width() / 2., h + 150),
                             ha='center', va='bottom', fontsize=9, fontweight='bold')
    plt.tight_layout()
    plt.savefig('figures/task1/class_distribution.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task1/class_distribution.png")

    # 5. Feature Preprocessing & Encoding
    print("\n" + "=" * 50)
    print("FEATURE PREPROCESSING & SPLITTING")
    print("=" * 50)

    # Exclude target labels and auxiliary metadata difficulty_level
    features_df = df.drop(columns=['attack_type', 'difficulty_level', 'attack_class', 'is_intrusion'])

    # Categorical columns to encode
    cat_cols = ['protocol_type', 'service', 'flag']
    print(f"Categorical features to LabelEncode: {cat_cols}")
    encoded_df = features_df.copy()
    label_encoders = {}
    for col in cat_cols:
        le = LabelEncoder()
        encoded_df[col] = le.fit_transform(encoded_df[col])
        label_encoders[col] = le
        print(f"  {col}: {len(le.classes_)} unique levels encoded")

    X = encoded_df.values
    y = df['is_intrusion'].values

    # Train-Test Split (80% training, 20% testing, stratified)
    print("\nSplitting dataset into 80% Training and 20% Testing sets (stratified)...")
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.20, random_state=42, stratify=y
    )
    print(f"  X_train shape: {X_train.shape}, y_train shape: {y_train.shape}")
    print(f"  X_test shape:  {X_test.shape}, y_test shape:  {y_test.shape}")
    print(f"  Training set intrusions: {np.sum(y_train)} / {len(y_train)} ({np.mean(y_train)*100:.2f}%)")
    print(f"  Testing set intrusions:  {np.sum(y_test)} / {len(y_test)} ({np.mean(y_test)*100:.2f}%)")

    # Standardization for SVM (fit on train, transform test)
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)

    # 6. Apply Three Supervised Classifiers
    models = {
        "Decision Tree": DecisionTreeClassifier(criterion='gini', max_depth=12, random_state=42),
        "Random Forest": RandomForestClassifier(n_estimators=100, max_depth=14, random_state=42, n_jobs=-1),
        "Support Vector Machine (SVM)": SVC(kernel='rbf', C=1.0, probability=True, random_state=42)
    }

    results = {}
    y_preds = {}
    y_probs = {}

    print("\n" + "=" * 50)
    print("TRAINING & EVALUATION BENCHMARKS")
    print("=" * 50)

    for name, model in models.items():
        print(f"\n---> Training {name}...")
        # SVM uses scaled features, tree models use unscaled
        cur_X_train = X_train_scaled if "SVM" in name else X_train
        cur_X_test = X_test_scaled if "SVM" in name else X_test

        t0 = time.time()
        model.fit(cur_X_train, y_train)
        train_time = time.time() - t0

        t0 = time.time()
        preds = model.predict(cur_X_test)
        infer_time = time.time() - t0

        probs = model.predict_proba(cur_X_test)[:, 1]

        acc = accuracy_score(y_test, preds)
        prec = precision_score(y_test, preds)
        rec = recall_score(y_test, preds)
        f1 = f1_score(y_test, preds)
        auc = roc_auc_score(y_test, probs)
        cm = confusion_matrix(y_test, preds)

        y_preds[name] = preds
        y_probs[name] = probs

        results[name] = {
            "Accuracy": acc,
            "Precision": prec,
            "Recall": rec,
            "F1_Score": f1,
            "ROC_AUC": auc,
            "Train_Time_s": train_time,
            "Infer_Time_s": infer_time,
            "Confusion_Matrix": cm.tolist(),
            "TN": int(cm[0, 0]),
            "FP": int(cm[0, 1]),
            "FN": int(cm[1, 0]),
            "TP": int(cm[1, 1])
        }

        print(f"     Train Time:  {train_time:.3f} s | Infer Time: {infer_time:.4f} s")
        print(f"     Accuracy:    {acc*100:.2f}%")
        print(f"     Precision:   {prec*100:.2f}%")
        print(f"     Recall:      {rec*100:.2f}%")
        print(f"     F1-Score:    {f1*100:.2f}%")
        print(f"     ROC-AUC:     {auc:.4f}")
        print(f"     Confusion Matrix: TN={cm[0,0]}, FP={cm[0,1]}, FN={cm[1,0]}, TP={cm[1,1]}")

    # 7. Generate Evaluation Figures
    # Figure 2: Confusion Matrices Side-by-Side
    fig, axes = plt.subplots(1, 3, figsize=(16, 4.5))
    cm_palettes = ['Blues', 'Greens', 'Purples']
    for idx, (name, res) in enumerate(results.items()):
        cm = np.array(res["Confusion_Matrix"])
        sns.heatmap(cm, annot=True, fmt='d', cmap=cm_palettes[idx], ax=axes[idx],
                    xticklabels=['Normal', 'Intrusion'], yticklabels=['Normal', 'Intrusion'],
                    cbar=False, annot_kws={"size": 13, "weight": "bold"})
        axes[idx].set_title(f"{name}\nAcc: {res['Accuracy']*100:.2f}% | F1: {res['F1_Score']*100:.2f}%",
                            fontsize=11, fontweight='bold')
        axes[idx].set_xlabel('Predicted Label')
        axes[idx].set_ylabel('True Label')
    plt.tight_layout()
    plt.savefig('figures/task1/confusion_matrices.png', dpi=300)
    plt.close()
    print("\n[+] Saved figures/task1/confusion_matrices.png")

    # Figure 3: ROC Curves
    plt.figure(figsize=(8, 6))
    colors = {'Decision Tree': '#e41a1c', 'Random Forest': '#377eb8', 'Support Vector Machine (SVM)': '#4daf4a'}
    for name, probs in y_probs.items():
        fpr, tpr, _ = roc_curve(y_test, probs)
        auc = results[name]["ROC_AUC"]
        plt.plot(fpr, tpr, label=f"{name} (AUC = {auc:.4f})", color=colors[name], linewidth=2.2)
    plt.plot([0, 1], [0, 1], 'k--', label='Random Baseline (AUC = 0.5000)', alpha=0.6)
    plt.xlim([-0.01, 1.0])
    plt.ylim([0.0, 1.02])
    plt.xlabel('False Positive Rate (1 - Specificity)', fontsize=11)
    plt.ylabel('True Positive Rate (Sensitivity / Recall)', fontsize=11)
    plt.title('Receiver Operating Characteristic (ROC) Comparison', fontsize=13, fontweight='bold')
    plt.legend(loc='lower right', frameon=True, fontsize=10)
    plt.grid(True, linestyle=':', alpha=0.6)
    plt.tight_layout()
    plt.savefig('figures/task1/roc_curves.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task1/roc_curves.png")

    # Figure 4: Feature Importance (Decision Tree and Random Forest)
    dt_importances = models["Decision Tree"].feature_importances_
    rf_importances = models["Random Forest"].feature_importances_
    feature_names = encoded_df.columns

    top_n = 10
    top_rf_idx = np.argsort(rf_importances)[::-1][:top_n]
    top_dt_idx = np.argsort(dt_importances)[::-1][:top_n]

    fig, axes = plt.subplots(1, 2, figsize=(15, 5.5))
    axes[0].barh(range(top_n), dt_importances[top_dt_idx][::-1], color='#e41a1c', alpha=0.85)
    axes[0].set_yticks(range(top_n))
    axes[0].set_yticklabels([feature_names[i] for i in top_dt_idx][::-1], fontsize=10)
    axes[0].set_xlabel('Gini Importance')
    axes[0].set_title('Decision Tree: Top 10 Features', fontsize=12, fontweight='bold')
    axes[0].grid(axis='x', linestyle=':', alpha=0.6)

    axes[1].barh(range(top_n), rf_importances[top_rf_idx][::-1], color='#377eb8', alpha=0.85)
    axes[1].set_yticks(range(top_n))
    axes[1].set_yticklabels([feature_names[i] for i in top_rf_idx][::-1], fontsize=10)
    axes[1].set_xlabel('Mean Decrease in Impurity')
    axes[1].set_title('Random Forest: Top 10 Features', fontsize=12, fontweight='bold')
    axes[1].grid(axis='x', linestyle=':', alpha=0.6)

    plt.tight_layout()
    plt.savefig('figures/task1/feature_importance.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task1/feature_importance.png")

    # Figure 5: Comparative Performance Metrics Bar Chart
    metrics_names = ['Accuracy', 'Precision', 'Recall', 'F1_Score', 'ROC_AUC']
    df_metrics = pd.DataFrame({
        m: [results[model][m] * 100 for model in models.keys()] for m in metrics_names
    }, index=list(models.keys()))

    plt.figure(figsize=(10, 5))
    x = np.arange(len(metrics_names))
    width = 0.25
    for i, model_name in enumerate(models.keys()):
        vals = [results[model_name][m] * 100 if m != 'ROC_AUC' else results[model_name][m] * 100 for m in metrics_names]
        bars = plt.bar(x + (i - 1) * width, vals, width, label=model_name, color=colors[model_name], alpha=0.9)
        for bar in bars:
            yval = bar.get_height()
            plt.text(bar.get_x() + bar.get_width()/2.0, yval - 7, f'{yval:.1f}%', ha='center', va='bottom',
                     color='white', fontweight='bold', fontsize=8, rotation=90)

    plt.xlabel('Evaluation Metrics', fontsize=11, fontweight='bold')
    plt.ylabel('Score (%)', fontsize=11, fontweight='bold')
    plt.title('Performance Comparison: DT vs RF vs SVM on NSL-KDD Test Set', fontsize=13, fontweight='bold')
    plt.xticks(x, ['Accuracy', 'Precision', 'Recall', 'F1-Score', 'ROC-AUC'], fontsize=10)
    plt.ylim([80, 103])
    plt.legend(loc='lower left', frameon=True, fontsize=10)
    plt.grid(axis='y', linestyle=':', alpha=0.6)
    plt.tight_layout()
    plt.savefig('figures/task1/performance_comparison.png', dpi=300)
    plt.close()
    print("[+] Saved figures/task1/performance_comparison.png")

    # Save summary JSON for PDF generator
    summary_data = {
        "dataset_shape": [int(df.shape[0]), int(df.shape[1])],
        "train_samples": int(len(X_train)),
        "test_samples": int(len(X_test)),
        "binary_distribution": {str(k): int(v) for k, v in binary_counts.items()},
        "multi_distribution": {str(k): int(v) for k, v in cat_counts.items()},
        "categorical_columns": cat_cols,
        "results": results,
        "top_features_rf": [feature_names[i] for i in top_rf_idx],
        "top_features_dt": [feature_names[i] for i in top_dt_idx]
    }
    with open("output/task1_results.json", "w") as f:
        json.dump(summary_data, f, indent=4)
    print("\n[+] Saved output/task1_results.json")
    print("\n[V] TASK 1 COMPLETED SUCCESSFULLY.")

if __name__ == '__main__':
    main()
